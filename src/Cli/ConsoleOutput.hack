/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Cli;

use HHPack\Codegen\Contract\Output;
use HH\Lib\{Str};
use SplFileObject;

final class ConsoleOutput implements Output {
  public function __construct(
    private SplFileObject $stdout = new SplFileObject("php://stdout"),
  ) {
  }

  public function info(string $message): void {
    $this->stdout->fwrite($message, Str\length($message));
  }
}
