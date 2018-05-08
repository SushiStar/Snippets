
def search4vowels(word:str) ->set:

<<<<<<< HEAD:python_scripts/vsearch.py
=======
def search4vowels(word:str)->set:

>>>>>>> 8ee91e366c55953afb79262f6f0fa5d31c7a4369:python_scripts/mymodules/vsearch.py
    """ Returns a boolean based on any vowels found """
    
    vowels = set('aeiou')
    found = vowels.intersection(set(word))
    return found

<<<<<<< HEAD:python_scripts/vsearch.py
def search4letters(phrase:str, letters:str = 'aeiou') ->set:
=======
def search4letters(phrase:str, letters:str = 'aeiou')->set:
>>>>>>> 8ee91e366c55953afb79262f6f0fa5d31c7a4369:python_scripts/mymodules/vsearch.py
    """ Return a set of the 'letters' found in 'phrase'. """
    return set(letters).intersection(set(phrase))
