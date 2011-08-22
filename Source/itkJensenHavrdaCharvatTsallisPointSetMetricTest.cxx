#include "itkJensenHavrdaCharvatTsallisPointSetMetric.h"

#include "itkLabeledPointSetFileReader.h"
#include "itkPointSet.h"

int itkJensenHavrdaCharvatTsallisPointSetMetricTest(
  int argc, char *argv[] )
{
  const unsigned int Dimension = 2;

  typedef float RealType;
  typedef itk::PointSet<RealType, Dimension> PointSetType;

  typedef itk::LabeledPointSetFileReader<PointSetType> ReaderType;

  ReaderType::Pointer fixedPointSetReader = ReaderType::New();
  fixedPointSetReader->SetFileName( argv[1] );
  fixedPointSetReader->Update();

  ReaderType::Pointer movingPointSetReader = ReaderType::New();
  movingPointSetReader->SetFileName( argv[2] );
  movingPointSetReader->Update();

  typedef itk::JensenHavrdaCharvatTsallisPointSetMetric<PointSetType>
    PointSetMetricType;
  PointSetMetricType::Pointer pointSetMetric = PointSetMetricType::New();
  pointSetMetric->SetMovingPointSet( movingPointSetReader->GetOutput() );
  pointSetMetric->SetMovingPointSetSigma( atof( argv[4] ) );
  pointSetMetric->SetMovingEvaluationKNeighborhood( 30 );
  pointSetMetric->SetFixedPointSet( fixedPointSetReader->GetOutput() );
  pointSetMetric->SetFixedPointSetSigma( atof( argv[3] ) );
  pointSetMetric->SetFixedEvaluationKNeighborhood( 30 );
  pointSetMetric->SetUseInputAsSamples( atoi( argv[7] ) );
  pointSetMetric->SetUseAnisotropicCovariances( atoi( argv[6] ) );
  pointSetMetric->SetUseRegularizationTerm( true );
  pointSetMetric->SetAlpha( atof( argv[5] ) );

  if( pointSetMetric->GetUseAnisotropicCovariances() )
    {
    pointSetMetric->SetFixedCovarianceKNeighborhood( 5 );
    pointSetMetric->SetFixedKernelSigma( 2 *
      pointSetMetric->GetFixedPointSetSigma() );
    pointSetMetric->SetMovingCovarianceKNeighborhood( 5 );
    pointSetMetric->SetMovingKernelSigma( 2 *
      pointSetMetric->GetMovingPointSetSigma() );
    }

  if( !pointSetMetric->GetUseInputAsSamples() )
    {
    pointSetMetric->SetNumberOfFixedSamples( 1000 );
    pointSetMetric->SetNumberOfMovingSamples( 1250 );
    }

  try
    {
    pointSetMetric->Initialize();

    PointSetMetricType::DefaultTransformType::ParametersType parameters;
    parameters.Fill( 0 );

    pointSetMetric->SetUseWithRespectToTheMovingPointSet( false );
    PointSetMetricType::DerivativeType gradientFixed;
    pointSetMetric->GetDerivative( parameters, gradientFixed );

//    std::cout << "Fixed gradient: " << std::endl;
//    std::cout << gradientFixed << std::endl;

    PointSetMetricType::MeasureType measureFixed
      = pointSetMetric->GetValue( parameters );

    std::cout << "Fixed value: " << std::endl;
    std::cout << measureFixed << std::endl << std::endl;

    PointSetMetricType::MeasureType measureFixedTest; 
    PointSetMetricType::DerivativeType gradientFixedTest;

    pointSetMetric->GetValueAndDerivative( parameters, 
      measureFixedTest, gradientFixedTest );

    if ( gradientFixed != gradientFixedTest )
      {
      std::cerr << "Error: gradients from GetValue() and GetValueAndDerivative() "
                << "differ. " << std::endl;
      return EXIT_FAILURE;          
      }
    if ( measureFixedTest != measureFixed )
      {
      std::cerr << "Error: fixed values from GetValue() and "  
                << "GetValueAndDerivative() differ. " << measureFixedTest << " != " 
                << measureFixed << std::endl;
      return EXIT_FAILURE;          
      }

    pointSetMetric->SetUseWithRespectToTheMovingPointSet( true );
    PointSetMetricType::DerivativeType gradientMoving;
    pointSetMetric->GetDerivative( parameters, gradientMoving );

//    std::cout << "Moving gradient: " << std::endl;
//    std::cout << gradientMoving << std::endl;

    PointSetMetricType::MeasureType measureMoving
      = pointSetMetric->GetValue( parameters );

    std::cout << "Moving value: " << std::endl;
    std::cout << measureMoving << std::endl;
    
    PointSetMetricType::MeasureType measureMovingTest; 
    PointSetMetricType::DerivativeType gradientMovingTest;

    pointSetMetric->GetValueAndDerivative( parameters, 
      measureMovingTest, gradientMovingTest );

    if ( measureMovingTest != measureMoving )
      {
      std::cerr << "Error: fixed values from GetValue() and "  
                << "GetValueAndDerivative() differ. " << measureMovingTest << " != " 
                << measureMoving << std::endl;
      return EXIT_FAILURE;          
      }
    if ( gradientMoving != gradientMovingTest )
      {
      std::cerr << "Error: gradients from GetValue() and GetValueAndDerivative() "
                << "differ. " << std::endl;
      return EXIT_FAILURE;          
      }


    }
  catch(...)
    {
    std::cerr << "JensenHavrdaCharvatTsallisPointSetMetricTest: "
              << " Exception thrown." << std::endl;
    return EXIT_FAILURE;
    }


  return EXIT_SUCCESS;
}

int main( int argc, char *argv[] )
{
  if( argc < 8 )
    {
    std::cerr << "Usage: " << argv[0] << " fixedPointSet movingPointSet "
              << "fixedSigma movingSigma alpha useAnisotropicCovariances "
              << "useInputAsSamples " << std::endl;
    return EXIT_FAILURE;
    }
  return itkJensenHavrdaCharvatTsallisPointSetMetricTest(
    argc, argv );

}

