const FEEDBACK_MESSAGE = {
  correct: "Correct!",
  incorrect: "Incorrect",
};

const multiQuestionFeedback = document.getElementById(
  "multi-question-feedback",
);
const multiQuestionButtons = document.querySelectorAll(".btn-multi-answer");

function cleanBtnSate(btn, currentBtnId) {
  if (btn.id !== currentBtnId) {
    btn.classList.value = [];
  }
}

for (const btn of multiQuestionButtons) {
  btn.addEventListener("click", (ev) => {
    multiQuestionFeedback.classList.remove("btn--valid", "btn--invalid");
    multiQuestionFeedback.classList.add("feedback");
    multiQuestionFeedback.classList.remove("hidden");

    if (ev.target.innerText === "443") {
      ev.target.classList.toggle("btn--valid");
      multiQuestionFeedback.classList.add("feedback--valid");
      multiQuestionFeedback.innerText = FEEDBACK_MESSAGE.correct;
    } else {
      ev.target.classList.toggle("btn--invalid");
      multiQuestionFeedback.classList.add("feedback--invalid");
      multiQuestionFeedback.innerText = FEEDBACK_MESSAGE.incorrect;
    }

    // Reset all others buttons
    let activeButtonsCount = 0;
    for (btn of multiQuestionButtons) {
      cleanBtnSate(btn, ev.target.id);

      if (
        btn.classList.contains("btn--valid") ||
        btn.classList.contains("btn--invalid")
      ) {
        activeButtonsCount++;
      }
    }

    // Hidde feedback if any button is active
    if (activeButtonsCount === 0) {
      multiQuestionFeedback.classList.add("hidden");
    }
  });
}

const freeQuestionForm = document.getElementById("free-question-form");
const freeQuestionInput = document.getElementById("free-question-input");
const freeQuestionFeedback = document.getElementById("free-question-feedback");

freeQuestionForm.addEventListener("submit", (ev) => {
  ev.preventDefault();

  freeQuestionFeedback.classList.value = [];
  freeQuestionFeedback.classList.add("feedback");
  freeQuestionFeedback.classList.remove("hidden");

  const answer = freeQuestionInput.value.trim().toLowerCase();
  if (answer === "https") {
    freeQuestionInput.classList.add("input--valid");
    freeQuestionFeedback.classList.add("feedback--valid");
    freeQuestionFeedback.innerText = FEEDBACK_MESSAGE.correct;
  } else {
    freeQuestionInput.classList.add("input--invalid");
    freeQuestionFeedback.classList.add("feedback--invalid");
    freeQuestionFeedback.innerText = FEEDBACK_MESSAGE.incorrect;
  }
});
