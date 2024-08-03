const API_URL = 'http://192.168.4.22'


const controlContainer = document.querySelector('.control-container')
let currButton = null;
let prevButton = null;


document.addEventListener('keydown', (e) => {
    let btnType;
    switch (e.key) {
        case 'ArrowUp':
            btnType = 'forward';
            break;
        case 'ArrowDown':
            btnType = 'backward';
            break;
        case 'ArrowLeft':
            btnType = 'left';
            break;
        case 'ArrowRight':
            btnType = 'right';
            break;
        default:
            return; 
    }

    const button = document.querySelector(`.control-btn[data-type="${btnType}"]`);
        if (button) {
            if (currButton !== null) {
                currButton.classList.remove('active')
                if (currButton.dataset.type === btnType) {
                    console.log('already clicked');
                    return
                }
            }
            currButton = button
            currButton.classList.add('active')
            button.click();
    }}
)


controlContainer.addEventListener('click', (e) => {
    const currButton = e.target.closest('.control-btn')
    if (currButton === null) {
        return
    }
    const btnType = currButton.dataset.type
    handleCarControl(btnType)
})


async function handleCarControl(btnType) {
    try {
        const request = `${API_URL}/control/${btnType}`
        console.log(request);
        const response = await fetch(request, {mode: 'no-cors'})
        console.log(response);
    } catch(e) {
        console.log('Error: ', e)
    }
}