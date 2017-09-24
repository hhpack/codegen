<?hh //strict

namespace HHPack\Codegen;

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

use Facebook\HackCodegen\{CodegenFile};

final class ClassFileGenerator {

  public function __construct(
    private OutputNamespace $namespace,
    private ClassFileGeneratable $generator,
  ) {}

  public function generate(string $name): CodegenFile {
    $className = $this->namespace->classNameOf($name);
    $relativeFilePath = $this->namespace->relativeClassFilePath($className);

    $newClass = new GenerateClass($className, $relativeFilePath);

    return $this->generator->generate($newClass);
  }

}
