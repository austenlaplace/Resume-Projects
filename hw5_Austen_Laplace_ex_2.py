#Homework 5 Exercise 2
#Austen Laplace
#Due 7 MAR 2019
#This program uses decorator functions to compute the fibonacci sequence
#Note - Calls using the @cache decorator - 19
#       Calls without using the @cache decorator - 177

#Import the functools module to use the the wraps function
import functools

#The cache decorator function creates a dictionary that holds the results of previous calls of the function
def cache(func):

    #Wrapper block for the cache decorator
    @functools.wraps(func)
    def wrapper_cache(*args, **kwargs):
        
        #Initialize the cache_key variable to hold the result of the current function call
        cache_key = args + tuple(kwargs.items())
        
        #If the current value of cache_key is not held within the dictonary, call the function
        if cache_key not in wrapper_cache.cache:
            wrapper_cache.cache[cache_key] = func(*args, **kwargs)
        
        #If the current value is already held within the dictionary, return the current value    
        return wrapper_cache.cache[cache_key]

    #Initialize the dictionary that will hold the results of the function calls
    wrapper_cache.cache = dict()
    return wrapper_cache

#The countCalls decorator function counts the number of times the function is called
def countCalls(func):
    
    #Wrapper block for the countCalls decorator
    @functools.wraps(func)
    def wrapper_countCalls(*args, **kwargs):
        
        #Print out the current number of calls of the function
        print(f"Call {wrapper_countCalls.numCalls} of the Fibonacci function")
        
        #Increment the counter by one
        wrapper_countCalls.numCalls += 1
        
        #Return the function
        return func(*args, **kwargs)

    #Initialize the numCalls variable to zero
    wrapper_countCalls.numCalls = 0
    return wrapper_countCalls

#The fibonacci function is decorated by the @countCalls and @cache decorator functions and calculates the value of the user input number of the Fibonacci sequence
@countCalls
@cache
def fibonacci(num):
    if num < 2:
        return num
    return fibonacci(num - 1) + fibonacci(num - 2)

#Prompt the user to enter the value they want to know the answer for
userInput = int(input("Enter the sequence number of the Fibonacci sequence you want to calculate: "))

#Print out the result of the fibonacci function with the argument of the user input value
print(fibonacci(userInput))

#Print out how many calls were made to the fibonacci function
print("The number of calls to the sequence function were: ")
print(fibonacci.numCalls)

