namespace HHPack\Codegen\Test\Mock;

use HHPack\Codegen\{ClassName};
use HHPack\Codegen\Contract\{FileGeneratable, NamedGenerator};
use Facebook\HackCodegen\{CodegenFile};

final class NamedGeneratorMock implements NamedGenerator {

  public function __construct(
    private string $name,
    private string $description,
    private FileGeneratable<ClassName> $generator,
  ) {}

  public function name(): string {
    return $this->name;
  }

  public function description(): string {
    return $this->description;
  }

  public function generate(ClassName $name): CodegenFile {
    return $this->generator->generate($name);
  }
}
