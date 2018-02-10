<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen;

use Facebook\HackCodegen\{ICodegenFactory, CodegenFile};

interface ClassFileGeneratable extends FileGeneratable<GenerateClass> {
  public function generate(GenerateClass $target): CodegenFile;
  public static function from(ICodegenFactory $factory): this;
}
