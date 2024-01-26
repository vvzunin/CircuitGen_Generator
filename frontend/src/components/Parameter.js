import React from 'react'

import gearImg from '../assets/gear.svg';
import select from '../assets/select.svg';
import noselect from '../assets/noselect.svg';

const Parameter = ({dataItem, deleteParameter, selectedParameters, setSelectedParameters}) => {

    const [isOpen, setIsOpen] = React.useState(false);

    const [status, setStatus] = React.useState(false);

    const updateSelected = (value) => {
        if (selectedParameters.includes(value)) {
          const updatedArray = selectedParameters.filter(item => item !== value);
          setSelectedParameters(updatedArray);
        } else {
          const updatedArray = [...selectedParameters, value];
          setSelectedParameters(updatedArray);
        }
      };
      

    return (
    <div className='parameter__wrapper'>
        <div className='parameter__main'>
            <div className="parameter__name">
                Параметр генерации #{dataItem.id}
            </div>
            <div className="parameter__buttons">
                {status && <div className="parameter__status select" onClick={() => {setStatus(false); updateSelected(dataItem.id);}}>
                    <img src={select}/>
                </div>}
                {!status && <div className="parameter__status noselect" onClick={() => {setStatus(true); updateSelected(dataItem.id);}}>
                    <img src={noselect}/>
                </div>}
                <button className='parameter__more' onClick={() => setIsOpen(!isOpen)}>{isOpen ? 'Скрыть' : 'Подробнее'}</button>
                <button className='parameter__delete'onClick={() => deleteParameter()}>Удалить</button>
            </div>
        </div>
    <div className={isOpen ? "parameter__info active" : "parameter__info"}>
        <div className="parameter__line"></div>
            <ul>
                <li>Тип генерации: {dataItem.type_of_generation}</li>
                <li>Минимальное количество входов: {dataItem.min_in}</li>
                <li>Максимальное количество входов: {dataItem.max_in}</li>
                <li>Минимальное количество выходов: {dataItem.min_out}</li>
                <li>Максимальное количество выходов: {dataItem.max_out}</li>
                <li>Количество повторений каждой комбинации: {dataItem.repeat_n}</li>
                <li>Сид генерации: {dataItem.seed}</li>
                {dataItem.type_of_generation === "From Random Truth Table" && <>
                    <li>Ограничение генерации: {dataItem.limit ? "true" : "false"}</li>
                    <li>CNFF: {dataItem.CNFF ? "true" : "false"}</li>
                    <li>CNFT: {dataItem.CNFT ? "true" : "false"}</li>
                </>}
                {dataItem.type_of_generation === "Rand Level" && <>
                    <li>Максимальное количество уровней: {dataItem.max_level}</li>
                    <li>Максимальное количество элементов: {dataItem.max_elem}</li>
                </>}
                {dataItem.type_of_generation === "Num Operation" && <>
                    <li>Оставлять пустые выходы: {dataItem.leave_empty_out ? "true" : "false"}</li>
                    <li>And: {dataItem.num_and}</li>
                    <li>Nand: {dataItem.num_nand}</li>
                    <li>Or: {dataItem.num_or}</li>
                    <li>Not: {dataItem.num_not}</li>
                    <li>Nor: {dataItem.num_nor}</li>
                    <li>Buf: {dataItem.num_buf}</li>
                    <li>Xor: {dataItem.num_xor}</li>
                    <li>Xnor: {dataItem.num_xnor}</li>
                </>}
                {dataItem.type_of_generation === "Genetic reproduction" && <>
                    <li>Размер популяции: {dataItem.population_size}</li>
                    <li>Количество циклов: {dataItem.cycles}</li>
                    <li>Коэффициент выхода: {dataItem.out_ratio}</li>
                    <li>Тип хромосомы: {dataItem.chromosome_type}</li>
                    <li>Тип отбора родителей: {dataItem.selection_type_parent}</li>
                    <li>Размер турнира: {dataItem.tour_size}</li>
                    <li>Тип воиспроизведения: {dataItem.playback_type}</li>
                    <li>Reference points: {dataItem.ref_points}</li>
                    <li>MaskProbability: {dataItem.mask_prob}</li>
                    <li>RecombinationNumber: {dataItem.rec_num}</li>
                </>}
                {dataItem.type_of_generation === "Genetic mutation" && <>
                    <li>Размер популяции: {dataItem.population}</li>
                    <li>Количество циклов: {dataItem.cycles}</li>
                    <li>Коэффициент выхода: {dataItem.u_out}</li>
                    <li>Тип хромосомы: {dataItem.chromosome_type}</li>
                    <li>Тип мутации: {dataItem.mut_type}</li>
                    <li>Вероятность мутации: {dataItem.mut_chance}</li>
                    <li>Тип обмена: {dataItem.swap_type}</li>
                    <li>Соотношение в таблице истинности: {dataItem.ratio_in_table}</li>
                </>}
                {dataItem.type_of_generation === "Genetic selection" && <>
                    <li>Размер популяции: {dataItem.population}</li>
                    <li>Количество циклов: {dataItem.cycles}</li>
                    <li>Коэффициент выхода: {dataItem.u_out}</li>
                    <li>Тип хромосомы: {dataItem.chromosome_type}</li>
                    <li>Тип отбора: {dataItem.selection_type}</li>
                    <li>Количество выживших: {dataItem.surv_num}</li>
                </>}
            </ul>
        </div>
    </div>
    )
}

export default Parameter;