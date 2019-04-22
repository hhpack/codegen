/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen;

use HHPack\Codegen\Contract\{FileGeneratable};

type GeneratorName = string;

type ClassName = string;

type PackageClassFileGeneratable = FileGeneratable<ClassName>;
