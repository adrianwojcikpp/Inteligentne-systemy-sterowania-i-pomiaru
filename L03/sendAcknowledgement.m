function sendAcknowledgement(u, ~)
% Read the data received from the other udpport instance. readline removes
% the terminator from the data read.
data = readline(u);

% Prepare the acknowledgement string.
dataDisp = "COMMAND RECEIVED - """ + data +  """";

disp(dataDisp);
writeline(u, "ACK: " + data, u.LocalHost, 9000);
end