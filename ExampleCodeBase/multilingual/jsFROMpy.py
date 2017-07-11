import PyV8
ctx = PyV8.JSContext()
ctx.enter()
print(PyV8.JSContext().eval(open("test.js").read()))
#ctx.eval("var template = 'Javascript in Python is {{ opinion }}';")
