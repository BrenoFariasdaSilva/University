# O desafio é criar um mecanismo por exemplo de "incremento por chamadas" sensível à história.
# Por exemplo:

# # Código:
# proximo = incremento(2)
# imprime(proximo())
# imprime(proximo())
# imprime(proximo())
# imprime(proximo())

# # Saída:
# 2
# 4
# 6
# 8

# Define the function "increment" that returns a function that increments a number by "n"
def increment(n):
    # Define a nested function "multiply" that returns the multiplication of "count" by "n"
    def multiply(count):
        return count * n
   # Define a nested function "calculate" that increments the variable "count" and returns its value multiplied by "n"
    def calculate():
        # Increment the variable "count" by 1
        calculate.count += 1
        result = multiply(calculate.count)
        return result
    # 
    calculate.count = 0
    # return the function "calculate"
    return calculate

# Create a variable "next" that receives the function "increment" with the parameter "2"
next = increment(2)
# Call the function "next" 4 times and print the result
print(next())
print(next())
print(next())
print(next())
# This works due to the fact that the function "increment" returns a function that is able to access the variable "n" from the outer function
# The n value in line 18 is 2, and this value is stored in the function "multiply" that is returned by the function "increment"