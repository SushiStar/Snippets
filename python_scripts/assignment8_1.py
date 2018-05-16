# coursera python for everybody assignment8

fname = input("Enter file name: ")
fh = open(fname)
word = list() 
for line in fh:
    linelist = line.split()
    for w in linelist:
        if w not in word: word.append(w)
word.sort()
print(word)
