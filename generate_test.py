

outfile = open("customs.i8", "wt")

outfile.write("5 10 51 100\nT P 3 10\nT N 5 20\n")

for i in range(4000000):
    outfile.write("P "+str(i+1)+"\n")
    
outfile.write("X")



outfile.close()