namespace HHPack\Codegen;

use Facebook\HackCodegen\{
  HackCodegenConfig,
  HackCodegenFactory,
  HackBuilderValues,
  CodegenFileResult,
  HackBuilderKeys,
  CodegenFile,
  CodegenClass,
  CodegenMethod,
};
use HHPack\Codegen\Cli\{Codegen};

function load_autoload_file(): void {
  $autoloadFiles = [
    __DIR__.'/../vendor/hh_autoload.php',
    __DIR__.'/../../../hh_autoload.php',
    __DIR__.'/../vendor/autoload.php',
    __DIR__.'/../../../autoload.php',
  ];
  $composerInstall = false;
  foreach ($autoloadFiles as $autoloadFile) {
    if (!\file_exists($autoloadFile)) {
      continue;
    }
    require $autoloadFile;
    $composerInstall = true;
    break;
  }
  if (!$composerInstall) {
    echo 'You must set up the dependencies, run the following commands:'.
      \PHP_EOL.
      'curl -s http://getcomposer.org/installer | php'.
      \PHP_EOL.
      'php composer.phar install'.
      \PHP_EOL;
    exit(1);
  }
}

<<__EntryPoint>>
function main(): noreturn {
  load_autoload_file();

  (new Codegen())->run(/* HH_IGNORE_ERROR[2050] */ $GLOBALS['argv']);

  exit(0);
}
