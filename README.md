# Pokemon-Ancestors

The world of Pokemon is very diverse and has a ton of lore. Within this Pokemon world it is mentioned that Pokemon are related but it is not explicit stated how each one is related to each other. Here I made a program that writes out all the ancestors of Legendary Pokemon based on an input file that list a direct ancestor.

The program works by parsing through the input file which lists a Pokemon and its direct descendant on each line (a directed acyclic graph). Each Pokemon is added to a hashmap that maps to a linked list of the Pokemon it is an ancestor to creating the graph. Once the graph is made, DFS is used from the starting nodes to find the desired Pokemon. When it’s found the value of the previous node’s hashmap (AKA the ancestor) is set to true and so on until all the ancestors are found.

The program creates an output file that lists out each Pokemon in alphabetical order and then writes all the ancestors that Pokemon would have based on the initial input file. For example Arceus is referred to as “The Original One” and is essentially the God Pokemon that created everything so he would be in the list of ancestors for all the Pokemon.
