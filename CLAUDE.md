<!--
  MOOSEDev project CLAUDE.md template.

  Drop this into a project that uses the MOOSEDev MCP server as its long-term memory, then
  fill the <PLACEHOLDERS>. It encodes the graph-first memory workflow (recall → capture →
  align → correct → validate) plus general engineering practices. The MOOSEDev repo's own
  CLAUDE.md additionally carries the product's design invariants; a consuming project does not
  need those — keep this file about how to *work* in the project, with the graph as memory.

  To seed an existing codebase's graph, ask your agent to bootstrap this repo's memory — the
  bootstrap skill is installed under `.claude/skills/` by `moosedev init`.
-->

# <PROJECT NAME>

<!-- One short paragraph: what this project is and why it exists. Keep it current. -->
<PROJECT DESCRIPTION>

<!-- moosedev:begin — MOOSEDev project-memory workflow. Managed by `moosedev init`; edit around this block freely, or delete the whole begin…end block to opt out. -->
> This project uses the **MOOSEDev** MCP server for durable, structured, long-term memory.
> The typed **project knowledge graph is the source of truth** for architectural decisions,
> lessons, constraints, requirements, and patterns — **not** markdown files. Free-text notes
> (e.g. `tasks/lessons.md`, `tasks/todo.md`) are optional human-readable mirrors, never canonical.

## Working with project memory (MOOSEDev)

When the `moosedev` MCP tools are available, prefer them over re-deriving context from scratch.
The loop:

1. **Recall first.** Before non-trivial work, surface prior decisions/lessons/constraints from
   the graph — and show the queries you ran. "Recall first" means a **list-all**
   `get_relevant_context` (no `topic`), not only a topic probe: a topic-scoped empty result
   means nothing cleared the relevance floor, **not** that the graph is empty.
2. **Capture as typed records.** Record durable knowledge as you go with
   `record_important_decision` (pick the right `kind`). Capture the decision **and its
   rationale** (and the rejected alternative), not transient chatter. Always report what was
   written (kind / title / returned IRI) — no silent writes.
3. **Align before coining.** Run `align_concepts` (or `suggest_mappings`) before introducing a
   new term, so the graph doesn't drift.
4. **Correct, don't duplicate.** `supersede_decision` when there is a replacement;
   `retract_decision` to deprecate one without a successor. Never silently duplicate — recall
   (list-all) first to confirm a record is genuinely new.
5. **Validate.** Run `validate_against_architecture` after capturing; resolve violations.

### Tool-selection ladder (cheap → precise)
- `get_relevant_context` — fast, deterministic, **shallow** lexical anchor/browse. Start here.
- `query` — walk-planned, synthesized natural-language answer **with a reasoning trace**. Use
  when you need reasoning over relationships, not just a label match. Keep questions short and
  focused (one question per call).
- `sparql` — exact, deterministic structural reads of the graph. Use for precise listings.

### Capture kinds
`ArchitecturalDecision` (the default — a choice + why + what was rejected) ·
`Constraint` (a hard limit/invariant) · `Requirement` (a goal/need) ·
`Pattern` (a deliberate recurring approach) · `AntiPattern` (something to avoid, + why) ·
`Lesson` (a non-obvious learning/gotcha).
<!-- moosedev:end -->

## Development practices

### 1. Plan Mode Default
- Enter plan mode for any non-trivial task (3+ steps or architectural decisions).
- If something goes wrong, STOP and re-plan — don't press on.
- Write detailed specs upfront to reduce ambiguity.

### 2. Subagent Strategy
- Use subagents liberally to keep the main context clean; offload research, exploration, and
  parallel analysis. One focused task per subagent.

### 3. Self-improvement Loop
- After ANY correction from the user: record a typed `Lesson` in the graph (the source of
  truth) capturing the Pattern and a rule that prevents the same mistake. Recall-first
  (list-all) so you don't duplicate an existing Lesson. Optionally mirror to `tasks/lessons.md`.
- Review prior Lessons at session start via `get_relevant_context` / `query`.

### 4. Verification before Done
- Never mark a task complete without proving it works (tests, logs, demonstrated behavior).
- Ask: "Would a staff engineer approve this?"

### 5. Demand Elegance (Balanced)
- For non-trivial changes, pause and ask "is there a more elegant way." Skip for simple,
  obvious fixes — don't over-engineer. Challenge your own work before presenting it.

### 6. Autonomous Bug Fixing
- Given a bug report or failing tests: just fix it. Point at logs/errors, then resolve them —
  minimal context-switching for the user.

## Core Principles
- **Simplicity first** — make every change as simple as possible; touch minimal code.
- **No laziness** — find root causes, no temporary fixes; senior-developer standards.
- **Minimal impact** — change only what's necessary; avoid introducing bugs.

## Setup (MOOSEDev memory)
<!-- How this project wires the moosedev MCP server. See MOOSEDev's README "Shared mode".
     Typically a repo-local .mcp.json (Claude) / .codex/config.toml (Codex) pointing at
     `moosedev --connect`, with MOOSEDEV_DATA_DIR set to a local store dir. Commit the
     store's kg.nq (the canonical project-graph text, maintained automatically) and
     gitignore the rest: `/.moosedev/*` + `!/.moosedev/kg.nq` — teammates who clone get
     the project's memory hydrated on first boot. -->
<SETUP NOTES>

## Project specifics
<!-- Fill in (or ask your agent to bootstrap this repo's memory — the bootstrap skill is
     installed under `.claude/skills/` by `moosedev init`): architecture
     overview, key modules, build/test commands, deployment, and known constraints. Durable
     items belong in the graph as typed records; keep this section a thin human-facing index. -->
<PROJECT SPECIFICS>
