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

use HHPack\Codegen\Contract\{NamedGenerator, GeneratorProvider};
use HHPack\Codegen\HackTest\{TestClassGenerator};
use HHPack\Codegen\Project\{PackageClassGenerator};
use function HHPack\Codegen\Cli\{define_generator, namespace_of};

final class Generators implements GeneratorProvider {
  const LIB = 'HHPack\\Codegen\\Example';
  const LIB_TEST = 'HHPack\\Codegen\\Example\\Test';

  public function generators(): Iterator<NamedGenerator> {
    /**
     * vendor/bin/codegen lib:class LibClass
     */
    yield define_generator("lib:class", "generate library class file.")
      ->mapTo(
        namespace_of(static::LIB, 'example/src')
          ->map(PackageClassGenerator::class),
      );

    /**
     * vendor/bin/codegen lib:testclass LibClassTest
     */
    yield define_generator("lib:testclass", "generate test class file.")
      ->mapTo(
        namespace_of(static::LIB_TEST, 'example/test')
          ->map(TestClassGenerator::class),
      );
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

The name of the generator is specified as the first argument, and the class name is specified as the second argument.

```shell
vendor/bin/codegen [GEN_NANE] LibClass
```

## Custom Generator

If you want to use your own generator, implement **ClassFileGeneratable**.

```hack
use HHPack\Codegen\{GenerateClassFile};
use HHPack\Codegen\Contract\{ClassFileGeneratable};
use Facebook\HackCodegen\{ICodegenFactory, CodegenFile, CodegenClass};

final class CustomClassGenerator implements ClassFileGeneratable {

  public function __construct(private ICodegenFactory $cg) {}

  public static function from(ICodegenFactory $factory): this {
    return new self($factory);
  }

  public function generate(GenerateClassFile $target): CodegenFile {
    return
      $this->cg
        ->codegenFile($target->fileName())
        ->setNamespace($target->belongsNamespace())
        ->addClass($this->classOf($target->name()));
  }

  private function classOf(string $className): CodegenClass {
    return $this->cg->codegenClass($className)->setIsFinal(true);
  }

}
```

You only need to specify it in the generator definition.  
In the example below, you can generate code with the command **vendor/bin/codegen myproject:loader MyLoader**.

```
yield define_generator("myproject:loader", "generate loader class file.")
  ->mapTo(
    namespace_of('MyProject\Loader', 'MyProject/Loader')
      ->map(CustomClassGenerator::class) // Map generator to namespace
    );
```

## Run the test

The test can be executed with the following command.

```shell
composer update
composer test
```
