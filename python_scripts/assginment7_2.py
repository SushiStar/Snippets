# Use the file name mbox-short.txt as the file name
fname = input("Enter file name: ")
fh = open(fname)
result = 0
count = 0
for line in fh:
    if not line.startwith('X-DSPAM-Confidence:'): coutinue
    line = line.split(':')
    result = result + float(line[1])
    count = count + 1
result = result/count
print('Average spam confidence: ' + str(result))
