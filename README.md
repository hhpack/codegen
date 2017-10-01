# Codegen

[![Build Status](https://travis-ci.org/hhpack/codegen.svg?branch=develop)](https://travis-ci.org/hhpack/codegen)

This package provides cli program to generate source code.  
You can map generators to **namespaces** in the configuration file.  

## Basic usage

### Create a generator configuration file

Create a configuration file that specifies the generator class.  
In the configuration file, you define the namespace and generator linkage.  

```hack
<?hh //strict

namespace MyPackage\Generators;

use HHPack\Codegen\{ GenerateType, ClassFileGenerator };
use HHPack\Codegen\Cli\{ GeneratorProvider };
use HHPack\Codegen\HackUnit\{ TestClassGenerator };
use HHPack\Codegen\Project\{ PackageClassGenerator };
use function HHPack\Codegen\Cli\{ namespace_of, library, library_test };

final class Generators implements GeneratorProvider {

  // Your package namespace
  const string PACKAGE_NAMESPACE = 'MyPackage';
  const string PACKAGE_TEST_NAMESPACE = 'MyPackage\Test';

  public function generators(): Iterator<Pair<GenerateType, ClassFileGenerator>> {
    // Link package namespace to generator
    yield library(
      namespace_of(static::PACKAGE_NAMESPACE, 'src')
        ->map(PackageClassGenerator::class));

    // Link package test namespace to generator
    yield library_test(
      namespace_of(static::PACKAGE_TEST_NAMESPACE, 'test')
        ->map(TestClassGenerator::class));
  }
}
```

### Append autoload settings to hh_autoload.json

Set the path to read the generator in **devRoots**.  
Please refer to [hhvm-autoload](https://github.com/hhvm/hhvm-autoload/blob/master/composer.json) for hh_autoload.json.

```json
{
  "roots": "src",
  "devRoots": "/path/to/"
}
```

### Generate class file for package

On the command line, specify **lib** and enter the class name.  
Then it creates a file **LibClass** in the **src** directory.  

```shell
vendor/bin/codegen lib LibClass
```

### Generate test class file for package

On the command line, specify **test** and enter the class name.  
Then it creates a file **LibClassTest** in the **test** directory.  

```shell
vendor/bin/codegen test LibClassTest
```

## Run the test

The test can be executed with the following command.

```shell
composer update
composer test
```
