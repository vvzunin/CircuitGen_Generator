import React from 'react'

import link from '../assets/link.svg';

const Scheme = ({data}) => {

    const [isOpen, setIsOpen] = React.useState(false);

    return (
    <div className='scheme__wrapper'>
        <div className='scheme__main'>
            <div className="scheme__name">
                Параметр генерации #{data.id}
            </div>
            <div className="scheme__buttons">
                <button className='scheme__more' onClick={() => setIsOpen(!isOpen)}>{isOpen ? 'Скрыть' : 'Подробнее'}</button>
                {data.link_of_parameter && data.link_of_parameter === "empty link" && <a className='scheme__show disabled'>Просмотреть</a>}
                {data.link_of_parameter && data.link_of_parameter !== "empty link" && <a className='scheme__show' href={data.link_of_parameter} target='_blank'>Просмотреть</a>}                
                {/* <div className='scheme__show'><img src={link} alt="link" /></div> */}
            </div>
        </div>
        <div className={isOpen ? "scheme__info active" : "scheme__info"}>
            <div className="scheme__line"></div>
            <ul>
                <li>Тип генерации: {data.type_of_generation}</li>
                <li>Минимальное количество входов: {data.min_in}</li>   
                <li>Максимальное количество входов: {data.max_in}</li>
                <li>Минимальное количество выходов: {data.min_out}</li>
                <li>Максимальное количество выходов: {data.max_out}</li>
                <li>Количество повторений каждой комбинации: {data.repeat_n}</li>
                <li>Сид генерации: {data.seed}</li>
                {data.type_of_generation === "From Random Truth Table" && <>
                    <li>Ограничение генерации: {data.limit ? "true" : "false"}</li>
                    <li>CNFF: {data.CNFF ? "true" : "false"}</li>
                    <li>CNFT: {data.CNFT ? "true" : "false"}</li>
                </>}
                {data.type_of_generation === "Rand Level" && <>
                    <li>Максимальное количество уровней: {data.max_level}</li>
                    <li>Максимальное количество элементов: {data.max_elem}</li>
                </>}
                {data.type_of_generation === "Num Operation" && <>
                    <li>Оставлять пустые выходы: {data.leave_empty_out ? "true" : "false"}</li>
                    <li>And: {data.num_and}</li>
                    <li>Nand: {data.num_nand}</li>
                    <li>Or: {data.num_or}</li>
                    <li>Not: {data.num_not}</li>
                    <li>Nor: {data.num_nor}</li>
                    <li>Buf: {data.num_buf}</li>
                    <li>Xor: {data.num_xor}</li>
                    <li>Xnor: {data.num_xnor}</li>
                </>}
                {data.type_of_generation === "Genetic reproduction" && <>
                    <li>Размер популяции: {data.population_size}</li>
                    <li>Количество циклов: {data.cycles}</li>
                    <li>Коэффициент выхода: {data.out_ratio}</li>
                    <li>Тип хромосомы: {data.chromosome_type}</li>
                    <li>Тип отбора родителей: {data.selection_type_parent}</li>
                    <li>Размер турнира: {data.tour_size}</li>
                    <li>Тип воиспроизведения: {data.playback_type}</li>
                    <li>Reference points: {data.ref_points}</li>
                    <li>MaskProbability: {data.mask_prob}</li>
                    <li>RecombinationNumber: {data.rec_num}</li>
                </>}
                {data.type_of_generation === "Genetic mutation" && <>
                    <li>Размер популяции: {data.population}</li>
                    <li>Количество циклов: {data.cycles}</li>
                    <li>Коэффициент выхода: {data.u_out}</li>
                    <li>Тип хромосомы: {data.chromosome_type}</li>
                    <li>Тип мутации: {data.mut_type}</li>
                    <li>Вероятность мутации: {data.mut_chance}</li>
                    <li>Тип обмена: {data.swap_type}</li>
                    <li>Соотношение в таблице истинности: {data.ratio_in_table}</li>
                </>}
                {data.type_of_generation === "Genetic selection" && <>
                    <li>Размер популяции: {data.population}</li>
                    <li>Количество циклов: {data.cycles}</li>
                    <li>Коэффициент выхода: {data.u_out}</li>
                    <li>Тип хромосомы: {data.chromosome_type}</li>
                    <li>Тип отбора: {data.selection_type}</li>
                    <li>Количество выживших: {data.surv_num}</li>
                </>}
            </ul>
        </div>
    </div>
    )
}

export default Scheme;