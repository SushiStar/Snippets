
def search4vowels(word:str) ->set:

    """ Returns a boolean based on any vowels found """
    
    vowels = set('aeiou')
    found = vowels.intersection(set(word))
    return found

def search4letters(phrase:str, letters:str = 'aeiou') ->set:
    """ Return a set of the 'letters' found in 'phrase'. """
    return set(letters).intersection(set(phrase))
