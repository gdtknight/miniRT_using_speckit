# Git Commit History

## 브랜치 전략

본 프로젝트는 **Git Flow** 전략을 따릅니다:

```
main (프로덕션)
  └── develop (통합 브랜치)
      └── feature/* (기능 브랜치)
```

## 커밋 컨벤션

**Conventional Commits** 형식을 따릅니다:

```
<type>(<scope>): <subject>

<body>
```

### Type 종류:
- `feat`: 새로운 기능 추가
- `fix`: 버그 수정
- `refactor`: 코드 리팩토링
- `docs`: 문서 수정
- `test`: 테스트 추가/수정
- `chore`: 빌드/설정 변경
- `ci`: CI/CD 설정
- `build`: 빌드 시스템 변경

## Feature 브랜치 히스토리

### 1. feature/project-structure
프로젝트 기본 구조 설정
- `chore(config)`: .gitignore 추가
- `build(makefile)`: Makefile 구성
- `feat(scenes)`: 테스트 씬 파일 추가

### 2. feature/vector-library
3D 벡터 수학 라이브러리
- `feat(vec3)`: vec3 구조체 및 생성자
- `feat(vec3)`: 산술 연산 (add, sub, mul, div)
- `feat(vec3)`: 기하 연산 (dot, cross, length, normalize)

### 3. feature/libft-utils
문자열/메모리 유틸리티
- `feat(libft)`: ft_strlen, ft_strdup, ft_split, ft_memcpy

### 4. feature/core-structures
핵심 데이터 구조
- `feat(core)`: 9개 구조체 정의 (t_vec3, t_ray, t_camera, etc.)

### 5. feature/parser
씬 파일 파서
- `feat(parser)`: 파서 유틸리티 함수
- `feat(parser)`: 오브젝트 파싱 함수
- `feat(parser)`: 메인 씬 파서

### 6. feature/ray-tracing-core
레이 트레이싱 엔진
- `feat(ray)`: 레이 생성 함수
- `feat(intersect)`: sphere 교차 함수
- `feat(intersect)`: plane 교차 함수
- `feat(intersect)`: cylinder 교차 함수

### 7. feature/lighting-system
조명 및 렌더링 시스템
- `feat(lighting)`: Phong 조명 모델
- `feat(render)`: 씬 렌더러 구현

### 8. feature/mlx-integration
MLX 통합 및 메인 프로그램
- `feat(bmp)`: BMP 파일 포맷 구조체
- `feat(bmp)`: BMP 파일 내보내기
- `feat(mlx)`: MLX 초기화
- `feat(mlx)`: 이벤트 핸들러
- `feat(main)`: 메인 프로그램 진입점

### 9. feature/tests
테스트 스위트
- `test`: 단위 및 통합 테스트 추가

## 최종 릴리스

### develop 브랜치
- `docs`: 프로젝트 문서 추가
- `ci`: GitHub Actions 워크플로우
- `chore(lib)`: MiniLibX 라이브러리 추가

### main 브랜치
- `release: v1.0.0`: 초기 레이 트레이서 구현

## 통계

- **총 커밋 수**: 37개
- **Feature 브랜치**: 9개
- **파일 추가**: 56개
- **코드 라인**: 3,410+ lines

## Git Graph

모든 feature 브랜치는 `--no-ff` 옵션으로 머지되어 브랜치 히스토리가 보존됩니다.

```bash
# Git 그래프 보기
git log --all --graph --decorate --oneline

# 상세 그래프 보기
git log --all --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr)%Creset' --abbrev-commit
```

## 주요 원칙

1. **기능별 브랜치 분리**: 각 기능은 독립적인 브랜치에서 개발
2. **작은 단위 커밋**: 하나의 커밋은 하나의 논리적 변경사항
3. **명확한 커밋 메시지**: 무엇을, 왜 변경했는지 명시
4. **머지 커밋 보존**: `--no-ff`로 브랜치 히스토리 유지
5. **컨벤션 준수**: Conventional Commits 형식 사용
