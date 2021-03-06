/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen;

use HHPack\Codegen\Contract\{FileGeneratable, ClassFileGeneratable};
use Facebook\HackCodegen\{CodegenFile};

final class ClassFileGenerator implements FileGeneratable<ClassName> {
  public function __construct(
    private OutputNamespace $namespace,
    private ClassFileGeneratable $generator,
  ) {}

  public function generate(ClassName $name): CodegenFile {
    $className = $this->namespace->classNameOf($name);
    $relativeFilePath = $this->namespace->relativeClassFilePath($className);

    $newClass = new GenerateClassFile($className, $relativeFilePath);

    return $this->generator->generate($newClass);
  }
}
