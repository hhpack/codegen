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

use HHPack\Codegen\{GenerateClass};
use HHPack\Codegen\Contract\{ClassFileGeneratable};
use Facebook\HackCodegen\{ICodegenFactory, CodegenFile, CodegenClass};

final class PackageClassGenerator implements ClassFileGeneratable {

  public function __construct(private ICodegenFactory $cg) {}

  public static function from(ICodegenFactory $factory): this {
    return new self($factory);
  }

  public function generate(GenerateClass $target): CodegenFile {
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
