# assignment 10 for coursera course python for everybody

name = input('Enter file:')
if len(name) < 1 : name = 'mbox-short.txt'
try:
    handle = open(name)
except:
    print('File cannot be opened.')

count = dict()

for line in handle:
    if line.startswith('From'):
        sentence = line.split()
        tm = sentence[5]
        h = tm.split(':')
        count[h[0]] = count.get(h[0],0) + 1

ll = list()
for k,v in count.items():
    ll.append((k,v))
ll = sorted(ll)
for a in ll:
    print(a[0], a[1])
