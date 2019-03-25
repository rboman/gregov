/**
 * \file Solver.cpp
 * \brief Implementation of the required function to load a SolverParams struct from file.
 */

#include <iostream>
#include <fstream>
#include <cerrno> //Change with something more c++ ;-)
#include <cstring>
#include <vector>
#include "Solver.hpp"

/**
 * \brief Load boundary conditions from a file
 * \param paramFile The file which has been previously opened.
 * \param solverParams The structure in which the parameters are loaded.
 * \param fileName The name of the parameters file which has been opened (for debug output).
 * \return true if the loading succeeds, false otherwise.
 */
static bool handleBoundaryCondition(std::ifstream& paramFile, SolverParams& solverParams,
                                    const std::string& fileName)
{
    bc boundary;
    unsigned int nBC = 0;

    while(true)
    {
        std::string bcName;
        std::string bcType;
        std::string tempBcCoeff;
        std::vector<double> bcCoeff;

        if(paramFile.eof())
        {
            std::cout << "End of file reached." << std::endl;
            break;
        }
        std::getline(paramFile, bcName);

        bc currentBC;

        std::getline(paramFile, bcType);
        if(bcType[0] != '\t') //Let's make them tabulated for easier reading
        {
            std::cerr << "Bad type format for BC  " << bcName
                      << " in parameter file " << fileName << std::endl;

            return false;
        }
        bcType.erase(0,1);

        if(bcType == "sinus")
            boundary.bcFunc = sinus;

        else if(bcType == "gaussian")
            boundary.bcFunc = gaussian;

        else if(bcType == "constant")
            boundary.bcFunc = constant;

        else if(bcType == "constantNeumann")
            boundary.bcFunc = constantNeumann;

        else if(bcType == "gaussian2D")
            boundary.bcFunc = gaussian2D;

        else
        {
            std::cerr << "Unhandled boundary condtion type " << bcType
                      << " for boundary " << bcName << " in parameter file "
                      << fileName <<std::endl;

            return false;
        }

        std::getline(paramFile, tempBcCoeff);
        if(tempBcCoeff[0] != '\t') //Let's make them tabulated for easier reading
        {
            std::cerr << "Bad coefficient format for BC  " << bcName
                      << " in parameter file " << fileName << std::endl;

            return false;
        }
        tempBcCoeff.erase(0,1);
        unsigned int precComaPos = -1;
        for(unsigned int i = 0 ; i < tempBcCoeff.size() ; ++i)
        {
            if(tempBcCoeff[i] == ',')
            {
                bcCoeff.push_back(std::stod(tempBcCoeff.substr(precComaPos + 1, i - precComaPos - 1)));
                precComaPos = i;
            }
        }
        //At the end, still one push_back to do
        bcCoeff.push_back(std::stod(tempBcCoeff.substr(precComaPos+1, tempBcCoeff.size() - precComaPos - 1)));

        boundary.coefficients = bcCoeff;

        solverParams.boundaryConditions[bcName] = boundary;

        nBC++;
    }

    std::cout << "Number of BC in file " << fileName << ": " << nBC << std::endl;

    return true;
}

//Documentation in .hpp
bool loadSolverParams(const std::string& fileName, SolverParams& solverParams)
{
    std::ifstream paramFile(fileName);

    if(!paramFile.is_open())
    {
        std::cerr << "Something went wrong when trying to read the file "
                  << fileName << std::endl
                  << std::strerror(errno) << std::endl;

        paramFile.close();
        return false;
    }

    std::string temp;
    std::getline(paramFile, temp);

    if(temp.compare(0, 5, "Gauss") != 0
       || !(temp.substr(5, temp.size() - 5).find_first_not_of("0123456789")
            == std::string::npos))
    {
        std::cerr << "Unexpected space integration type " << temp
                  << " in parameter file " << fileName << std::endl;

        paramFile.close();
        return false;
    }


    solverParams.spaceIntType = temp;

    temp.clear();
    std::getline(paramFile, temp);

    if(!(temp == "Lagrange" || temp == "Isoparametric"))
    {
        std::cerr << "Unexpected basis function type " << temp
                  << " in parameter file " << fileName << std::endl;

        paramFile.close();
        return false;
    }

    solverParams.basisFuncType = temp;

    temp.clear();
    std::getline(paramFile, temp);

    if(!(temp == "RK1" || temp == "RK4"))
    {
        std::cerr << "Unexpected time integration type " << temp
                  << " in parameter file " << fileName << std::endl;

        paramFile.close();
        return false;
    }

    solverParams.timeIntType = temp;

    temp.clear();
    std::getline(paramFile, temp);

    if(!(temp == "strong" || temp == "weak"))
    {
        std::cerr << "Unexpected solver type " << temp
                  << " in parameter file " << fileName << std::endl;

        paramFile.close();
        return false;
    }

    solverParams.solverType = temp;

    temp.clear();
    std::getline(paramFile, temp);

    if(!(temp.find_first_not_of("0123456789") == std::string::npos)) //To improve
    {
        std::cerr << "Unexpected simulation time duration " << temp
                  << " in parameter file " << fileName << std::endl;

        paramFile.close();
        return false;
    }

    solverParams.simTime = std::stoi(temp);

    temp.clear();
    std::getline(paramFile, temp);

    if(!(temp.find_first_not_of(".0123456789") == std::string::npos)) //To improve
    {
        std::cerr << "Unexpected time step " << temp
                  << " in parameter file " << fileName << std::endl;

        paramFile.close();
        return false;
    }

    solverParams.timeStep = std::stod(temp);

    if(!handleBoundaryCondition(paramFile, solverParams, fileName))
    {
        paramFile.close();
        return false;
    }

    paramFile.close();

    // display the parameters
    std::cout   << "Number of Gauss points: " << solverParams.spaceIntType
                << std::endl
                << "Type of basis function: " << solverParams.basisFuncType
                << std::endl
                << "Time intgeration scheme: " << solverParams.timeIntType
                << std::endl
                << "Formulation type: " << solverParams.solverType
                << std::endl
                << "Simulation time duration: " << solverParams.simTime << "s"
                << std::endl
                << "Time step: " << solverParams.timeStep << "s"
                << std::endl;

    return true;
}
