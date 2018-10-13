#include "http.h"
#include "structs.h"


QueueHandle_t *queue_data_http;
color_data_t color_data;

WebServer server(80);
const char *ssid = WLAN_SSID;
const char *password = PASSWORD;

void parse_json_data(String *message) {
    StaticJsonBuffer<800> JSONBuffer;
    JsonObject &parsed = JSONBuffer.parseObject(*message);
    if (!parsed.success()) {   //Check for errors in parsing
        Serial.println("Parsing failed");
        delay(5000);
        return;
    }

    Serial.println("Parsing Array");
    const char *mode1;
    for (uint8_t i = 0; i < DATA_SIZE; i++) {
        color_data.color_array[i].red = parsed["color_array"][i]["color_red"];
        color_data.color_array[i].green = parsed["color_array"][i]["color_green"];
        color_data.color_array[i].blue = parsed["color_array"][i]["color_blue"];
    }
    color_data.time = parsed["time"];
    mode1 = parsed["mode"];
    color_data.number_of_colors = parsed["number_of_colors"];

    strcpy(color_data.mode, mode1);

}

void handle_request_body() { //Handler for the body path

    if (server.hasArg("plain") == false) { //Check if body received
        server.send(200, "text/plain", "Body not received");
        return;
    }
    String message = server.arg("plain");
    server.send(200, "text/plain", message);

    parse_json_data(&message);

    Serial.println("Array parsed, sending Queue");
    xQueueSend(*queue_data_http, &color_data, portMAX_DELAY);
}

void http_init(QueueHandle_t *queue_data1) {

    Serial.println("HTTP_TASK");

    queue_data_http = queue_data1;

    Serial.println("Wifi init");
    WiFi.begin(ssid, password);  //Connect to the WiFi network
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
        delay(500);
        Serial.println("Waiting to connect...");
    }
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP
    server.on("/body", handle_request_body); //Associate the handler function to the path
    server.begin(); //Start the server
    Serial.println("Server listening");
}