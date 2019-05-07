#include <functional>
#include "field.hpp"
#include "../matrices/matrix.hpp"
#include "../params/Params.hpp"
#include "../mesh/Mesh.hpp"
#include "../utils/utils.hpp"

//typedef to lighten the notations
typedef std::function<void(double t, Field& field, CompleteField& compField,
                    const Matrix& matrix, const Mesh& mesh,
                    const SolverParams& solverParams, const DomainDiv& domainDiv, unsigned int rank)> UsedF;

typedef std::function<void(double t, Field& field, PartialField& partialField,
         CompleteField& compField, const Matrix& matrix, const DomainDiv& domainDiv,
         unsigned int rank, const Mesh& mesh, const SolverParams& solverParams,
         Field& temp, UsedF usedF)> IntegScheme;


/**
 * \brief Compute the numerical time integration using the method of Runge-Kutta order 1
    i.e. explicit Euler
 * \param t Current time.
 * \param field Field that contains all the main variables.
 * \param partialField Field that contains all the main variables (private)
 * \param matrix Structure that contains the matrices of the DG method.
 * \param mesh Mesh representing the domain.
 * \param solverParams Parameters of the solver.
 * \param temp temporary Field needed to compute the different k's
 * \param usedF pointer to the function Fweak or Fstrong
 */
void RK1(double t, Field& field, PartialField& partialField,
         CompleteField& compField, const Matrix& matrix, const DomainDiv& domainDiv,
         unsigned int rank, const Mesh& mesh, const SolverParams& solverParams,
         Field& temp, UsedF usedF);


/**
 * \brief Compute the numerical time integration using the method of Runge-Kutta order 2
    i.e. explicit Euler
 * \param t Current time.
 * \param field Field that contains all the main variables.
 * \param partialField Field that contains all the main variables (private)
 * \param matrix Structure that contains the matrices of the DG method.
 * \param mesh Mesh representing the domain.
 * \param solverParams Parameters of the solver.
 * \param temp temporary Field needed to compute the different k's
 * \param usedF pointer to the function Fweak or Fstrong
 */
void RK2(double t, Field& field, PartialField& partialField,
         CompleteField& compField, const Matrix& matrix, const DomainDiv& domainDiv,
         unsigned int rank, const Mesh& mesh, const SolverParams& solverParams,
         Field& temp, UsedF usedF);


/**
 * \brief Compute the numerical time integration using the method of Runge-Kutta order 3
    i.e. explicit Euler
 * \param t Current time.
 * \param field Field that contains all the main variables.
 * \param partialField Field that contains all the main variables (private)
 * \param matrix Structure that contains the matrices of the DG method.
 * \param mesh Mesh representing the domain.
 * \param solverParams Parameters of the solver.
 * \param temp temporary Field needed to compute the different k's
 * \param usedF pointer to the function Fweak or Fstrong
 */
void RK3(double t, Field& field, PartialField& partialField,
         CompleteField& compField, const Matrix& matrix, const DomainDiv& domainDiv,
         unsigned int rank, const Mesh& mesh, const SolverParams& solverParams,
         Field& temp, UsedF usedF);


/**
 * \brief Compute the numerical time integration using the method of Runge-Kutta order 4
    i.e. explicit Euler
 * \param t Current time.
 * \param field Field that contains all the main variables.
 * \param partialField Field that contains all the main variables (private)
 * \param matrix Structure that contains the matrices of the DG method.
 * \param mesh Mesh representing the domain.
 * \param solverParams Parameters of the solver.
 * \param temp temporary Field needed to compute the different k's
 * \param usedF pointer to the function Fweak or Fstrong
 */
void RK4(double t, Field& field, PartialField& partialField,
         CompleteField& compField, const Matrix& matrix, const DomainDiv& domainDiv,
         unsigned int rank, const Mesh& mesh, const SolverParams& solverParams,
         Field& temp, UsedF usedF);