# Designing Classes

## Strategy-based solution
* Design classes for easy change
* Design classes for easy extensions
* Don't guess! If you expect change, prefer design that makes this change easy. If you
  don't expect any change, learn from the next change.

## Template-based Solution
* Classes should be concise and focused on one purpose
* Classes should be developed with extensibility in mind
* Classes should be split into smaller pieces to favour reuse

## Data Member Initialization
* Avoid writing an empty default constructor
* Define and initialise member variables in the order of member declaration
* Prefer initialization to assignment in constructors
* Use delegating constructors to represent common actions for all constructors of a class.
* Prefer default constructors to be simple and non-throwing
* Prefer in-class initializers to member initializers in constructors for constant
  initializers
* Prefer to initialize pointer members to nullptr with in-class member initializers.
* By default, declare single-argument constructors explicit.
* Consider the alignment of data members when adding member data to a struct or class.
* Define and initialize member variables in the order of member declaration.
* By default, make member functions const
* Const correctness is part of the semantics of your class.

## Visibility vs. Accessibility
Remember the four steps of the compiler to resolve a function call:
1. Name lookup: Select all (visible) candidate functions with a certain name within the
   current scope. If none is found, proceed into the next surrounding scope.
2. Overload resolution: Find the best match among the selected candidate functions. If
   necessary, apply the necessary argument conversions.
3. Access labels: Check if the best match is accessible from the given call site.
4. =delete: Check if the best match has been explicitly deleted.

