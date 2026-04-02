# Task: Expression calculator
Need to write a multithread server application on c++ to calculate math expressions. Application will get input value “(3+2*4)*7” on TCP socket. The end of expression symbol is new line character ‘\n’. The result of the calculation result should be written back to the socket.
After getting and calculation should continue serving other expressions from that socket(socket shouldn’t be closed). Server should be able to serve many clients(>10000) at the same time. Clients’ requests should be served concurrently (no more than free cpu cores at the same time). For implementing network input/output could be used any ubuntu library (please describe the dependency if needed for build). For testing could be used any client (netcat,telnet). Input expression could be upto 1GB. Processing 1 Gb of expression shouldn’t take more than several minutes. Expression should consist only from round number (not float). Should be supported operations -(subtraction), +(plus), (multiplication), (divide) and brackets according priorities. For ensure that it works well it would be a plus to write generator of input test sequences and unit tests for developed components. It would be a plus to see nice and clean code, with well read.me, description of how to install, run test and run application

# Todo
- [ ] Setup cmake project 
- [ ] Implement TCP server (handle multiple clients concurrently)
- [ ] Implement expression parser and calculator (supporting +, -, *, /, and brackets), ensuring it can handle large expressions (up to 1GB) efficiently 
- [ ] Write unit tests for expression parser and calculator
- [ ] Write a generator for input test sequences
- [ ] Create a README file with installation instructions, how to run tests, and how to run the application
- [ ] Optimize performance to ensure processing 1GB of expression takes no more than several minutes
- [ ] Code is clean and well-documented