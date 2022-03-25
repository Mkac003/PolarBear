import string

stn = ""
ls = list(string.ascii_lowercase)
for i in range(0, 10):
  ls.append(str(i))

for i in range(0, 13):
  ls.append(f"F{i}")

for char in ls:
  stn = stn+f"int PB_{char} = SDLK_{char};\n"

print(stn)
