# [10번 과제] 언리얼 모듈과 플러그인 (ModuleAndPlugin)

## 프로젝트 개요
이 프로젝트는 언리얼 엔진의 핵심 계층 구조(솔루션 - 프로젝트/플러그인 - 모듈 - 소스코드)를 파악하기 위해 진행되었습니다. 에디터의 자동화 기능을 최소화하고, 수동으로 모듈과 플러그인 폴더 체계를 구축하여 엔진이 빌드 타임과 런타임에 종속성을 어떻게 관리하는지 학습했습니다.

## 최종 프로젝트 구조
프로젝트는 크게 주 게임 모듈(`ModuleAndPlugin`)과 독립된 플러그인(`MyNBCLog`)으로 구성되어 있으며, 플러그인 내부에 커스텀 로그를 담당하는 `MySpartaLog` 모듈이 포함되어 있습니다.

- **ModuleAndPlugin (Primary Game Module)**
  - `TestActor`를 스폰하여 플러그인 모듈의 기능을 호출하는 역할입니다.
- **Plugins / MyNBCLog (Plugin)**
  - `MyNBCLog.uplugin`: 플러그인의 메타데이터 및 포함될 모듈 로드 정보를 설정합니다.
  - **Source / MySpartaLog (Plugin Module)**
    - `MySpartaLog.Build.cs`: 모듈 종속성(`Core`, `Engine` 등)을 정의합니다.
    - `MySpartaLog.h / .cpp`: `IModuleInterface`를 상속받아 모듈의 시작/종료 제어 및 커스텀 로그 카테고리(`LogMySpartaModule`)를 구현합니다.
    - `TestActor.h / .cpp`: 주 모듈에서 스폰 시 커스텀 로그를 출력하는 테스트용 액터입니다.

## 구현 단계 요약
1. **프로젝트 생성**: C++ 기반 Third Person 샘플 프로젝트(`ModuleAndPlugin`)를 생성했습니다.
2. **모듈 제작**: `Source` 폴더 하위에 수동으로 `MySpartaLog` 모듈 구조를 만들고, 커스텀 로그 매크로(`MYSPARTALOG_API`)를 정의했습니다.
3. **모듈 연결**: `.uproject`와 `Target.cs`를 수정하여 새 모듈을 빌드 대상에 포함시키고, `TestActor`를 통해 상호작용 성공을 확인했습니다.
4. **플러그인으로 업그레이드**: 기능 재사용성을 높이기 위해 `Plugins/MyNBCLog` 폴더를 생성하고, 기존 `MySpartaLog` 모듈을 플러그인 내부로 마이그레이션(이동)했습니다.
5. **플러그인 활성화**: `.uproject`를 갱신하여 플러그인을 활성화(`Enabled: true`)하고 독립적인 동작을 검증했습니다.

## Trouble Shooting (TIL)
과제 진행 중 발생한 주요 문제와 해결 과정입니다.

* **Issue 1: MSB3073 에러 (코드 8)**
  * **원인**: 수동으로 모듈 파일 생성 시 윈도우 설정에 의해 확장자가 `.txt`로 이중 저장되거나, 모듈 폴더의 계층 위치가 어긋나 Unreal Build Tool(UBT)이 세팅 파일을 찾지 못해 발생했습니다.
  * **해결**: 파일 확장명 숨기기를 해제하여 정확한 확장자로 변경하고, 모듈 폴더를 `Source/` 바로 아래(병렬)로 위치시켜 해결했습니다.
* **Issue 2: C2065 식별자 선언 에러**
  * **원인**: `TestActor.cpp`에서 커스텀 로그를 호출했으나, 해당 카테고리가 선언된 헤더 파일을 포함하지 않아 발생했습니다.
  * **해결**: `TestActor.cpp` 상단에 `#include "MySpartaLog.h"`를 추가하여 종속성을 명확히 연결했습니다.
