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

use Facebook\HackCodegen\{CodegenFile};

final class DefinedGenerator implements FileGeneratable<string> {

  public function __construct(
    private DefinedMetaData $meta,
    private FileGeneratable<string> $generator,
  ) {}

  public function name(): string {
    return $this->meta->name();
  }

  public function description(): string {
    return $this->meta->description();
  }

  public function generate(string $name): CodegenFile {
    return $this->generator->generate($name);
  }
}
