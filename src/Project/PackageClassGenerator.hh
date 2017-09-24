<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Project;

use HHPack\Codegen\{GenerateClass, ClassFileGeneratable};
use Facebook\HackCodegen\{ICodegenFactory, CodegenFile, CodegenClass};

final class PackageClassGenerator implements ClassFileGeneratable {

  public function __construct(private ICodegenFactory $cg) {}

  public function generate(GenerateClass $class): CodegenFile {
    return
      $this->cg
        ->codegenFile($class->fileName())
        ->setIsStrict(true)
        ->setNamespace($class->belongsNamespace())
        ->addClass($this->classOf($class->name()));
  }

  private function classOf(string $className): CodegenClass {
    return $this->cg->codegenClass($className)->setIsFinal(true);
  }

}
