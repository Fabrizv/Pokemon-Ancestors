// Name: Fabrizio Valdivia
// Description: This program takes in a file of parents and children and then
//      shows the ancestors to every node
#include <unordered_map>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Function: ancestors(std::string, std::string, std::unordered_map<std::string, std::list<std::string>>,
//            std::unordered_map<std::string, bool >, std::unordered_map<std::string, bool>)
// Description: Finds the ancestors of a particular node and sets them to true in listOfAncestors
bool ancestors(std::string current, std::string searchName,
            std::unordered_map< std::string, std::list<std::string> > famTree,
            std::unordered_map< std::string, bool > & visited,
            std::unordered_map< std::string, bool > & listOfAncestors)
{
    // Checks if the current node is the node we are looking for
    //      If so return true
    if (current == searchName)
        return true;

    // Mark the current node as having been visted
    visited[current] = true;

    // Iterate through famTree, 
    //      If you havent visted the next node call ancestors and check if its true
    //      If it is set the current ListOfAncestors to true
    for (auto x = famTree[current].begin(); x != famTree[current].end (); x++)
        if (!visited[*x])
            if (ancestors(*x, searchName, famTree, visited, listOfAncestors))
                listOfAncestors[current] = true;

    // Sets all the visited nodes to false
    for (auto x = famTree[current].begin(); x != famTree[current].end (); x++)
        visited[current] = false;
    
    //If the current node is an ancestor return true, else return false
    if (listOfAncestors[current])
        return true;
    else 
        return false;
}

// Function: main()
// Description: Reads in a file gets the parents and children and puts them into unordered maps 
//      It finds the ancestors for every node, puts them into vectors, sorts them, and then outputs them
int main()
{
    // Declare variables
    std::string input, searchName;
    std::string line, partOfLine;
    std::string from, to;

    std::vector<std::string> names;
    std::unordered_map< std::string, std::list<std::string> > adjList;
    std::unordered_map< std::string, bool > isNeighbor;
    std::unordered_map< std::string, bool > temp;
    
    // Ask user for file name and open it
    std::cout << "Enter file: ";
    std::cin >> input;
    std::ifstream inFile(input);
    
    // Loop through each line to get the 'from' and 'to'
    while (std::getline(inFile, line))
    {
        // String stream to get parts of the line
        std::stringstream ss(line);
        getline(ss, from, '>');

        // Use pop_back to delete the extra space at the end
        from.pop_back();
        from.pop_back();

        // Get the throwaway part and then the 'to'
        getline(ss, partOfLine, ' ');
        getline(ss, to, '\n');

        // Add the strings to the corresponding unordered maps
        adjList[from].push_back(to);
        isNeighbor[from] = true;
        temp[from] = true;
        temp[to] = true;
    }
    
    // Loop through temp hashmap and add it to names vector
    for (auto a: temp)
        names.push_back(a.first);

    // Sort the names vector
    std::sort(names.begin(), names.end());

    std::ofstream newFile("output.txt");

    // Loops for every name in the names vector
    for (int z = 0; z < names.size(); z++)
    {
        // Declares variables
        std::unordered_map< std::string, bool > finalMap;
        std::vector<std::string> noNeighbor;
        std::vector<std::string> finalNames;

        // Outputs the name of the relative
        newFile << "Pokemon Name: " << names[z] << std::endl;
        
        // Loops through the names and then loops through the decendents
        //      Everyone who is a decendent of someone gets set to false in the isNeighbor unordered map
        //      If the node for isNeighbor is true push the name into the noNeighbor vector
        for (int i = 0; i < names.size(); i++)
        {
            for ( auto d = adjList[names[i]].begin (); d != adjList [names[i]].end(); d++)
                isNeighbor[*d] = false;

            if (isNeighbor[names[i]])
                noNeighbor.push_back(names[i]);
        }
        
        // Loops through the noNeighbor vector
        for (int i = 0; i < noNeighbor.size(); i++)
        {    
            // Initializes two unordered maps and sets all their nodes to 0
            std::unordered_map<std::string, bool >  visited;
            std::unordered_map<std::string, bool> listOfAncestors;
            for (int k = 0; k < names.size(); k++)
            {    
                visited[names[k]] = false;
                listOfAncestors[names[k]] = false;
            }

            // Call ancestors functions, and if it's true loop through names
            //      If the node is an ancestor then add it to the finalMap unordered map
            if (ancestors(noNeighbor[i], names[z], adjList, visited, listOfAncestors))
                for (int j = 0; j < names.size(); j++)
                    if (listOfAncestors[names[j]] == true)
                        finalMap[names[j]] = true;
        }

        // Tells the user the list of the ancestors
        newFile << "List of ancestors:" <<std::endl;
        
        // Puts the finalMap names into the finalNames vector
        for (auto a: finalMap)
            finalNames.push_back(a.first);

        // Sorts the finalNames vector
        std::sort(finalNames.begin(), finalNames.end());

        // If the sixe of the vector was 0 output "None"
        if (finalNames.size() == 0)
            newFile << "None" << std::endl;

        // Output the names of all the ancestors 
        for (int i = 0; i < finalNames.size(); i++)
            newFile << finalNames[i] << std::endl;

        // Output a new line
        newFile << std::endl;
    }
    newFile.close();

    inFile.close();
    return 0;
}