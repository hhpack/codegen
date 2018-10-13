<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\HackTest;

use HHPack\Codegen\{GenerateClassFile};
use HHPack\Codegen\Contract\{FileGeneratable, ClassFileGeneratable};
use Facebook\HackCodegen\{
  ICodegenFactory,
  CodegenFile,
  CodegenClass,
  CodegenMethod,
};

final class TestClassGenerator implements ClassFileGeneratable {

  public function __construct(private ICodegenFactory $cg) {}

  public static function from(ICodegenFactory $factory): this {
    return new self($factory);
  }

  public function generate(GenerateClassFile $target): CodegenFile {
    return $this->cg
      ->codegenFile($target->fileName())
      ->setNamespace($target->belongsNamespace())
      ->useType('Facebook\HackTest\HackTest')
      ->useFunction('Facebook\FBExpect\expect')
      ->addClass($this->classOf($target->name()));
  }

  private function classOf(string $className): CodegenClass {
    return $this->cg
      ->codegenClass($className)
      ->setExtends('HackTest')
      ->setIsFinal(true)
      ->addMethod($this->exampleTestMethod());
  }

  private function exampleTestMethod(): CodegenMethod {
    return $this->cg
      ->codegenMethod('testExample')
      ->setReturnType('void')
      ->setBody('expect(true)->toBeTrue();');
  }

}
