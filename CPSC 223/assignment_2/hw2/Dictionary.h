#ifndef DICTIONARY_H
#define DICTIONARY_H

// Key-value dictionary abstract class
template<class K, class V>
class Dictionary {
    public:
        // Virtual destructor
        virtual ~Dictionary() { }
		
		Dictionary& operator=(const Tree& other)
		
		

        // Add a given key, value pair to the dictionary.  If key is already
        // a key in the dictionary, REPLACE the associated value.
        virtual void add(K key, V value) = 0;

        // Return the value associated with the given key
        virtual V getValue(K key) const = 0;

        // Return the key associated with the given value.  In the case where
        // multiple values are equal to the passed-in value, returning any
        // associated key is correct.
        virtual K getKey(V value) const = 0;

        // Remove the given key and associated value from the dictionary.  In
        // the case where key doesn't exist, this function should either
        // silently continue running, call abort(), or fail an assertion.
        virtual void remove(K key) = 0;

        // Display the dictionary on standard output, indicating what keys are
        // associated with what values.  The order of keys can be in any order.
        virtual void display() const = 0;

        // Return the number of key-value pairs in this dictionary.
        virtual int size() const = 0;

        // Returns true if the key exists and false otherwise.
        virtual bool keyExists(K key) const = 0;
};

#endif