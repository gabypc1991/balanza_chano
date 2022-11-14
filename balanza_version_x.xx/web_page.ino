void webExc(){
  WiFiClient client = server.available();
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            read_dht();
            read_balanza();
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
            if(header.indexOf("GET /index") >= 0){pagina = "index";}
            if(header.indexOf("GET /factor_100") >= 0){factor_scale += 100; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /factor_1000") >= 0){factor_scale += 1000; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /factor_10000") >= 0){factor_scale += 10000; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /factor_100000") >= 0){factor_scale += 100000; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /factor_-100") >= 0){factor_scale -= 100; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /factor_-1000") >= 0){factor_scale -= 1000; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /factor_-10000") >= 0){factor_scale -= 10000; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /factor_-100000") >= 0){factor_scale -= 100000; scale.set_scale(factor_scale); pagina = "index";}
            if(header.indexOf("GET /edit_hora_1") >= 0){pagina = "edit_hora_1";}
            if(header.indexOf("GET /edit_hora_2") >= 0){pagina = "edit_hora_2";}
            if(header.indexOf("GET /edit_hora_3") >= 0){pagina = "edit_hora_3";}
            if(header.indexOf("GET /edit_hora_4") >= 0){pagina = "edit_hora_4";}
            if(header.indexOf("GET /edit_hora_5") >= 0){pagina = "edit_hora_5";}
            if(pagina == "index"){html_inicio(client);}            

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop 
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");  
          }
  }

void html_inicio(WiFiClient client){
  // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println(".button3 { background-color: #AFFF33; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button32 {background-color: #358220;}");
            client.println("table {table-layout: fixed;width: 100%;border-collapse: collapse;border: 3px solid purple;}");
            client.println("th, td {padding: 10px;}");
            client.println(".button4 { background-color: #195B6A; border: none; color: white; padding: 6px 12px;}");
            client.println(".humedad {font-family: Helvetica;color: black;font-size: 18px;text-align: left;font-weight: bold;}");
            client.println(".fechaHora {font-family: Helvetica;color: black;font-size: 18px;text-align: right;}</style></head>");
            

            // Web Page Heading
            client.println("<body><h1>BALANZA MODULAR x 4 (1000 Kg. Max.)</h1>");
            client.println("<p class =\"fechaHora\">" + read_rtc() + "</p>");
            client.println("<p class =\"humedad\">Humedad: " + String(h) + " %</p>");
            client.println("<p class =\"humedad\">Temperatura: " + String(t) + " C</p>");
            client.println("<p class =\"humedad\">Peso: " + String(lectura_balanza, 2) + " Kg.</p>");
            client.println("<p class =\"humedad\">Factor: " + String(factor_scale) + " u.</p>");

             client.println("<table class=\"tabla1\">");
             client.println("<caption>Calibrar Factor</caption>");
             client.println("<tbody>");
             client.println("<tr>");
             client.println("<td></td>");
             client.println("<th>Edit 1</th>");
             client.println("<th>Edit 2</th>");
             client.println("<th>Edit 3</th>");             
             client.println("<th>Edit 4</th>");
             client.println("</tr>");
             client.println("<tr>");
             client.println("<th>1</th>");             
             client.println("<td><a href=\"/factor_100\"><button class=\"button4\">+100</button></a></td>");
             client.println("<td><a href=\"/factor_1000\"><button class=\"button4\">+1000</button></a></td>");
             client.println("<td><a href=\"/factor_10000\"><button class=\"button4\">+10000</button></a></td>");             
             client.println("<td><a href=\"/factor_100000\"><button class=\"button4\">+100000</button></a></td>");
             client.println("</tr>");
             client.println("<tr>");
             client.println("<th>2</th>");
             client.println("<td><a href=\"/factor_-100\"><button class=\"button4\">-100</button></a></td>");
             client.println("<td><a href=\"/factor_-1000\"><button class=\"button4\">-1000</button></a></td>");
             client.println("<td><a href=\"/factor_-10000\"><button class=\"button4\">-10000</button></a></td>");
             client.println("<td><a href=\"/factor_-100000\"><button class=\"button4\">-100000</button></a></td>");
             client.println("</tr>");         
             client.println("</tbody>");
             client.println("</table>");
             
             client.println("</body></html>");
  }
