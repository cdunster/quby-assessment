# Quby Assessment

## The Task
We have some systems that gather samples from all kinds of measurements and report them to a service. There are other systems that request the current value for some of these parameters from this service. Your assignment is to implement this service. It is to be implemented in the C language. We suggest using a library called ezxml to handle the XML parts of the assignment. You are free to modify it where needed.

This service has 2 implementation platforms:
1. An Embedded IoT platform for the Client
    1. Battery Operated
    1. Connects every 15 min to the server
    1. Uses an MCU ((we suggest a ARM M0+ one, you can change it but you’ll be requested why) with 32KB RAM and 256KB Flash.
1. An Linux Platform for the Server

### Detailed description
The measuring clients report these measurements by sending a XML messages over TCP to port 6423 of some registry service .The xml messages consist of a root tag called ‘update’, inside it there is any number of (unique) keys as tags, with values as text content.

For example:
```xml
<update>
    <personsPassed>12</personsPassed>
    <lightCondition>bright</lightCondition>
    <humidity>52</humidiy>
</update>
```

Once the payload is delivered the client can either send another update or disconnect. On the other side of this service there will be several systems that request the current status for either some specific values, or for all of the currently known values. They connect to the service in the same way as the measurement devices. When connected they send an XML message with a root tag called ‘retrieve’ having 0..x child tags called ‘key’ and the name of the desired parameter as character content. When it specifies no parameters the server returns all the known parameters.

For example:
```xml
<retrieve/>
```

To retrieve all currently known values, or
```xml
<retrieve>
    <key>personsPassed</key>
    <key>humidity</key>
</retrieve>
```
to retrieve the current value for the ‘personsPassed’ and ‘humidity’ parameters. The server should return an XML message with parent tag ‘status’ and a child tag per requested parameter having the name of the parameter as tag name and the value of the parameter as character value.

Like so:
```xml
<status>
    <personsPassed>12</personsPassed>
    <humidity>52</humidiy>
</status>
```

After receiving this update the client can either request more parameters or close the connection. The output XML of the service should be ‘prettyfied’, similar to the examples (indent child nodes), so that when a human ‘client’ queries the system the output is easy to read. When the service is shut-down and re-started it should start up with the last known state for all the parameters. When a client sends an invalid request the service should return nothing and close the connection.

## The Implementation

### Activity Diagrams
The following activity diagrams have been created in VisualParadigm community edition, the project can be found in the VisualParadigm directory.

#### Measuring Client
This is the activity diagram between the Measuring Client and the Central Service.

![Measuring Client activity diagram](/Documentation/UML/Measurement Client Activity Diagram.jpg?raw=true "Measuring Client activity diagram")

#### Request Client
This is the activity diagram between the Request Client and the Central Service.

![Request Client activity diagram](/Documentation/UML/Request Client Activity Diagram.jpg?raw=true "Request Client activity diagram")
