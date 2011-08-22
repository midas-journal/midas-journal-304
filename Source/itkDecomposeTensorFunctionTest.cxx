
#include "itkDecomposeTensorFunction.h"

#include "itkVariableSizeMatrix.h"

int itkDecomposeTensorFunctionTest( int argc, char *argv[] )
{
  typedef itk::VariableSizeMatrix<float> InputMatrixType; 

  typedef itk::DecomposeTensorFunction<InputMatrixType> DecomposerType; 
  DecomposerType::Pointer decomposer = DecomposerType::New();

  typedef DecomposerType::OutputMatrixType OutputMatrixType; 
 
  InputMatrixType M( 3, 3 );
  M(0, 0) = 1; 
  M(0, 1) = 2; 
  M(0, 2) = 3; 
  M(1, 0) = 2; 
  M(1, 1) = 5; 
  M(1, 2) = 4; 
  M(2, 0) = 3; 
  M(2, 1) = 4; 
  M(2, 2) = 9; 
 
  /**
   * Eigen-Decomposition
   */
  OutputMatrixType D, V;
  try
    {
    decomposer->EvaluateEigenDecomposition( M, D, V );
    }
  catch(...)
    {
    std::cerr << "EvaluateEigenDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  

  /**
   * Symmetric Eigen-Decomposition
   */
  OutputMatrixType Ds, Vs;
  try
    {
    decomposer->EvaluateSymmetricEigenDecomposition( M, Ds, Vs );
    }
  catch(...)
    {
    std::cerr << "EvaluateSymmetricEigenDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  
  
  /**
   * Right polar decomposition
   */
  OutputMatrixType Rrp, Srp;
  try
    {
    decomposer->EvaluateRightPolarDecomposition( M, Rrp, Srp );
    }
  catch(...)
    {
    std::cerr << "EvaluateRightPolarDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  
  
  /**
   * Left polar decomposition
   */
  OutputMatrixType Rlp, Slp;
  try
    {
    decomposer->EvaluateLeftPolarDecomposition( M, Slp, Rlp );
    }
  catch(...)
    {
    std::cerr << "EvaluateLeftPolarDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  
  
  /**
   * QR decomposition
   */
  OutputMatrixType Q, R;
  try
    {
    decomposer->EvaluateQRDecomposition( M, Q, R );
    }
  catch(...)
    {
    std::cerr << "EvaluateQRDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  
  
  /**
   * SVD decomposition
   */
  OutputMatrixType Usvd, Vsvd, Wsvd;
  try
    {
    decomposer->EvaluateSVDDecomposition( M, Usvd, Wsvd, Vsvd );
    }
  catch(...)
    {
    std::cerr << "EvaluateSVDDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  
  
  /**
   * SVD economy decomposition
   */
  OutputMatrixType Ve, We;
  try
    {
    decomposer->EvaluateSVDEconomyDecomposition( M, We, Ve );
    }
  catch(...)
    {
    std::cerr << "EvaluateSVDEconomyDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  
  
  /**
   * Cholesky decomposition
   */
  OutputMatrixType L;
  try
    {
    decomposer->EvaluateCholeskyDecomposition( M, L );
    }
  catch(...)
    {
    std::cerr << "EvaluateCholeskyDecomposition:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  

  /**
   * Determinant
   */
  try
    {
    decomposer->EvaluateDeterminant( M );
    }
  catch(...)
    {
    std::cerr << "EvaluateDeterminant:  Exception thrown." 
              << std::endl; 
    return EXIT_FAILURE;
    }  

  return EXIT_SUCCESS;
}

int main( int argc, char *argv[] )
{
  if( argc < 1 )
    {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return EXIT_FAILURE;
    }
  return itkDecomposeTensorFunctionTest( argc, argv );

}

