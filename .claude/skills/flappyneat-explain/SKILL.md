---
name: flappyneat-explain
description: >
  Explains a just-built system in the FlappyNEAT project at interview-ready depth.
  Use this skill whenever the user says "explain this", "walk me through it",
  "explain the system", "break it down", "how does X work", "/explain", or after
  any new system has been implemented and the user wants to understand it well
  enough to explain it to someone else. The user (intermediate C++, familiar with
  OpenGL) wants to own every file as if they wrote it themselves — explanations
  should be pitched at "I could answer an interview question about this" depth.
---

# FlappyNEAT Explain Skill

The user is building FlappyNEAT as a portfolio piece. They want to understand every
system well enough to explain it confidently in a technical interview — even though
an agent wrote the code. Your job is to give them that ownership.

## User profile

- **C++ level:** Intermediate — comfortable with classes, pointers, STL. Not deep on templates or move semantics.
- **OpenGL level:** Familiar — has built something small before, understands the pipeline.
- **Goal:** Be able to explain any file or line of code as though they wrote it.

## What to produce

Read the file(s) the user is asking about (or the most recently written system if not specified), then produce a structured breakdown:

---

### 1. The one-sentence summary
What does this system do in plain English? No jargon yet.

### 2. The big picture — why does it exist?
What problem does it solve? What would break if you removed it? Explain the *need* before the *solution*.

### 3. Key design decisions
For each non-obvious design choice in the code, explain:
- What was chosen
- Why that choice (what alternatives exist and why they were ruled out)
- What trade-off it involves

Keep this to 3–5 decisions max — the ones that actually matter.

### 4. How the pieces connect
Trace the data flow or call chain through the system. Use the actual function/class names from the code. The user should be able to mentally trace execution after reading this.

### 5. Interview questions — and how to answer them
Give 3 realistic technical interview questions someone might ask about this system, followed by strong answers. Frame answers in first person ("I chose X because...") so the user can practice saying them.

### 6. One thing to watch out for
One gotcha, edge case, or subtle invariant in this code that a new developer could easily miss. This is the thing that shows you really read it.

---

## Style

- Use the actual names from the code (class names, function names, variable names) — this helps the user recognise what they're reading about when they look at the file.
- Explain *why*, not just *what*. The user can read the what themselves.
- Keep each section tight. This isn't a tutorial — it's a study guide.
- Don't patronise — the user is smart and technically capable. Just bridge the gaps.
