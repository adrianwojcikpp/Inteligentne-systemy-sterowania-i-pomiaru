with open('sine_wave.csv', 'r') as file1:
    with open('sine_from_server.csv', 'r') as file2:
        difference = set(file1).difference(file2)

difference.discard('\n')

with open('diff.txt', 'w') as file_out:
    for line in difference:
        file_out.write(line)