print('Loading module...')
import example_module as m


print("\n\n#1 Testing 'print_stdout'...")
m.print_stdout()


print("\n\n#2 Testing 'parse_postional_arguments'...")
a, b, c = 1, 4.5591, 'Hello'
print(f'Parsing int={a}; float={b}; str={c};')
m.parse_postional_arguments(a, b, c)


print("\n\n#3 Testing 'parse_named_arguments'...")
a, b, c = 1, 4.5591, 'Hello'
print(f'Parsing a:int={a}; b:float={b}; c:str={c}...')
m.parse_named_arguments(a, b, c) 
# Or also: m.parse_named_arguments(a=a, b=b, c=c)
print(f'Parsing empty...')
m.parse_named_arguments()


print("\n\n#4 Testing 'parse_positional_and_named_arguments'...")
a, b = 'aaa', 'bbb'
foo, bar, baz = 'zzfoo', 'zzbar', 'zzbaz'
print(f'Positional: a={a} b={b}')
print(f'Named: foo={foo}, bar={bar}, baz={baz}')
m.parse_positional_and_named_arguments(a, b, foo=foo, bar=bar, baz=baz)
print(f'Parsing empty named arguments...')
m.parse_positional_and_named_arguments(a, b)


print("\n\n#5 Testing 'parse_iterable'...")
a_list = [1, 2, 3 ,4]
print(f'Testing list of floats: {a_list}...')
m.parse_iterable(a_list)
print(f'Testing empty list...')
m.parse_iterable([])
