# assignment8_2  coursera python for everybody

fname = input("Enter file name: ")
if len(fname) < 1 : fname = "mbox-short.txt"

try:
    fh = open(fname)
except:
    print("Cannot open file: ", fname)
    quit()
count = 0
for line in fh:
    if line.startswith("From "):
        count= count + 1
        temp = line.split()
        print(temp[1])
print("There were", count, "lines in the file with From as the first word")
