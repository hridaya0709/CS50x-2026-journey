const bar = document.getElementById('bar');
const close = document.getElementById('close');
const nav = document.getElementById('navbar');
const landOnTest = document.getElementById('landOnTest');

if (bar) {
    bar.addEventListener('click', () => {
        nav.classList.add('active');
    })
}

if (close) {
    close.addEventListener('click', () => {
        nav.classList.remove('active');
    })
}

if (landOnTest) {
    landOnTest.addEventListener('click', () => {
        window.location.href = "test.html";
    })
}

const testForm = document.getElementById('testForm');
const questionsDiv = document.getElementById('questions');
const resultDiv = document.getElementById('result');
const resultTitle = document.getElementById('resultTitle');
const resultDesc = document.getElementById('resultDesc');
const retakeBtn = document.getElementById('retakeTest');
const testDiv = document.getElementById('test');

// Score range per question is 1-10, 5 questions => total range 5-50.
// Adjust these bucket boundaries/copy to match your types.html descriptions.
const personalityTypes = [
    { min: 5,  max: 12, name: 'Soft/Cute',       desc: 'Kawaii, cutesy and hyper feminine vibes, celebrates innocence, positivity and self-expression, doll like persona.' },
    { min: 13, max: 19, name: 'Y2K',             desc: 'Retro-futuristic style, love exploring new trends and technologies but also loves nostalgic celebration of life.' },
    { min: 20, max: 26, name: 'Fashionista',     desc: 'Passionate about fashions, keeps up with the latest trends, confident, carries an attitude of creativity and influential among others.' },
    { min: 27, max: 33, name: 'Nerdy/Corporate', desc: 'Deeply engaged in academic spirits, intellectual pursuits, loves reading and passionate about a dedicated lifestyle.' },
    { min: 34, max: 41, name: 'Princess',        desc: 'Hyper feminine and elegant visual style, inspired by fairy tales and historical royalty and shows that the fantasies can be brought to reality.' },
    { min: 42, max: 50, name: 'Grunge',          desc: 'Late 1980s and early 1990s vibes, reflects a sense of authenticity, emphasizes individuality and rebellion against norms.' },
];

const TOTAL_QUESTIONS = 5;

if (testForm) {
    testForm.addEventListener('submit', (e) => {
        e.preventDefault(); 

        let score = 0;
        const unanswered = [];

        for (let i = 1; i <= TOTAL_QUESTIONS; i++) {
            const selected = testForm.querySelector(`input[name="q${i}"]:checked`);
            if (!selected) {
                unanswered.push(i);
            } else {
                score += parseInt(selected.value, 10);
            }
        }

        if (unanswered.length > 0) {
            alert(`Please answer question(s): ${unanswered.join(', ')}`);
            return;
        }

        const result = personalityTypes.find(t => score >= t.min && score <= t.max);

        resultTitle.textContent = result.name;
        resultDesc.textContent = result.desc;

        questionsDiv.style.display = 'none';
        resultDiv.style.display = 'block';

        testDiv.classList.add('result');
    });
}

if (retakeBtn) {
    retakeBtn.addEventListener('click', () => {
        testForm.reset();
        resultDiv.style.display = 'none';
        questionsDiv.style.display = 'block';
        testDiv.classList.remove('result');
    });
}
