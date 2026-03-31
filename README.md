# [10번 과제] 언리얼 모듈과 플러그인 (ModuleAndPlugin)

## 프로젝트 개요
[cite_start]이 프로젝트는 언리얼 엔진의 핵심 계층 구조(솔루션 - 프로젝트/플러그인 - 모듈 - 소스코드)를 파악하기 위해 진행되었습니다 [cite: 15-16]. 
[cite_start]에디터의 자동화 기능을 최소화하고, 수동으로 모듈과 플러그인 폴더 체계를 구축하여 엔진이 빌드 타임과 런타임에 종속성을 어떻게 관리하는지 학습했습니다 [cite: 18-19, 127].

## 최종 프로젝트 구조
[cite_start]프로젝트는 크게 주 게임 모듈(`ModuleAndPlugin`)과 독립된 플러그인(`MyNBCLog`)으로 구성되어 있으며, 플러그인 내부에 커스텀 로그를 담당하는 `MySpartaLog` 모듈이 포함되어 있습니다[cite: 154, 334].

- **ModuleAndPlugin (Primary Game Module)**
  - [cite_start]`TestActor`를 스폰하여 플러그인 모듈의 기능을 호출하는 역할 [cite: 323-325].
- [cite_start]**Plugins / MyNBCLog (Plugin)** [cite: 330-332]
  - [cite_start]`MyNBCLog.uplugin`: 플러그인 메타데이터 및 모듈 로드 설정 [cite: 336-353].
  - [cite_start]**Source / MySpartaLog (Plugin Module)** [cite: 334]
    - [cite_start]`MySpartaLog.Build.cs`: 모듈 종속성(`Core`, `Engine` 등) 정의 [cite: 189-204].
    - [cite_start]`MySpartaLog.h / .cpp`: `IModuleInterface`를 상속받아 모듈의 시작/종료 제어 및 커스텀 로그 카테고리(`LogMySpartaModule`) 구현 [cite: 205-225].
    - [cite_start]`TestActor.h / .cpp`: 주 모듈에서 스폰 시 커스텀 로그를 출력하는 테스트용 액터 [cite: 293-320].

## 구현 단계 요약
1. [cite_start]**프로젝트 생성**: C++ 기반 Third Person 샘플 프로젝트(`ModuleAndPlugin`) 생성 [cite: 158-159].
2. [cite_start]**모듈 제작**: `Source` 폴더 하위에 수동으로 `MySpartaLog` 모듈 구조를 만들고, 커스텀 로그 매크로(`MYSPARTALOG_API`)를 정의함 [cite: 181-225].
3. [cite_start]**모듈 연결**: `.uproject`와 `Target.cs`를 수정하여 새 모듈을 빌드 대상에 포함시키고 [cite: 226-292][cite_start], `TestActor`를 통해 상호작용 성공 확인함 [cite: 293-326].
4. [cite_start]**플러그인으로 업그레이드**: 기능 재사용성을 높이기 위해 `Plugins/MyNBCLog` 폴더를 생성하고, 기존 `MySpartaLog` 모듈을 플러그인 내부로 마이그레이션(이동)함 [cite: 327-353].
5. [cite_start]**플러그인 활성화**: `.uproject`를 갱신하여 플러그인을 활성화(`Enabled: true`)하고 독립적인 동작을 검증함 [cite: 354-392].

## Trouble Shooting
과제 진행 중 발생한 주요 문제와 해결 과정입니다.

* **Issue 1: MSB3073 에러 (코드 8)**
  * **원인**: 수동으로 모듈 파일(`Build.cs` 등) 생성 시 윈도우 설정에 의해 확장자가 `.txt`로 이중 저장되거나, 모듈 폴더의 계층 위치가 어긋나 Unreal Build Tool(UBT)이 세팅 파일을 찾지 못해 발생.
  * **해결**: 파일 확장명 숨기기를 해제하여 정확한 `.cs`, `.cpp`, `.h` 확장자로 변경하고, 모듈 폴더를 다른 모듈 내부가 아닌 `Source/` 바로 아래(병렬)로 위치시켜 해결함.
* **Issue 2: C2065 식별자 선언 에러**
  * **원인**: `TestActor.cpp`에서 커스텀 로그 `LogMySpartaModule`을 호출했으나, 해당 카테고리가 선언된 헤더 파일을 포함하지 않음.
  * [cite_start]**해결**: `TestActor.cpp` 상단에 `#include "MySpartaLog.h"`를 추가하여 종속성을 명확히 연결함[cite: 309].
