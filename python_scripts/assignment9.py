# assignment9   coursera course python for everybody

name = input("Enter file:")
if len(name) < 1 : name = "mbox-short.txt"
handle = open(name)

container = dict()

for line in handle:
    if line.startswith('From:'):
        word = line.split()
        container[word[1]] = container.get(word[1],0) + 1

count = 0
temp=[]

for t in container.items() :
    if count < t[1]:
        count = t[1]
        temp = t[0]
print(temp, count)
