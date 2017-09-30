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

use HHPack\Codegen\{OutputNamespace, GenerateType, ClassFileGenerator};

function generate_namespace_of(string $name, string $path): OutputNamespace {
  return new OutputNamespace($name, $path);
}

function library(
  ClassFileGenerator $generator,
): Pair<GenerateType, ClassFileGenerator> {
  return Pair {GenerateType::LibraryClass, $generator};
}

function library_test(
  ClassFileGenerator $generator,
): Pair<GenerateType, ClassFileGenerator> {
  return Pair {GenerateType::TestClass, $generator};
}
