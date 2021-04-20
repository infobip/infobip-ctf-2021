import code

c = code.InteractiveConsole()
print("Python 3.9.0 (default, Oct 22 2020, 05:03:39)")
print("[GCC 9.3.0] on linux")
print('Type "help", "copyright", "credits" or "license" for more information.')
while True:
	try:
		inp = c.raw_input(">>> ")
		if len(inp) > 5:
			raise ValueError("no inputs longer than 5 allowed")
		if c.push(inp):
			c.resetbuffer()
	except KeyboardInterrupt:
		break
	except Exception as e:
		print(e)
