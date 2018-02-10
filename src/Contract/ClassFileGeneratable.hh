<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Contract;

use HHPack\Codegen\{GenerateClass};
use Facebook\HackCodegen\{ICodegenFactory, CodegenFile};

/**
 * An interface that can generate class files.
 */
interface ClassFileGeneratable extends FileGeneratable<GenerateClass> {
  /**
   * Generate a class file with the specification of the specified class.
   */
  public function generate(GenerateClass $target): CodegenFile;

  /**
   * Generate an instance based on the factory of the generator.
   */
  public static function from(ICodegenFactory $factory): this;
}
