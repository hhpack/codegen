<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Cli;

use HHPack\Codegen\{OutputNamespace, GeneratorName};

function define_generator(
  GeneratorName $name,
  string $description,
): GeneratorMapper {
  return new GeneratorMapper(new DefinedMetaData($name, $description));
}

function namespace_of(string $name, string $path): OutputNamespace {
  return new OutputNamespace($name, $path);
}
