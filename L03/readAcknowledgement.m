function readAcknowledgement(u, ~)
% Read the acknowledgement data. readline removes the Terminator from the
% data read.
data = readline(u);

% Display the acknowledgement string read.
disp(data);
end