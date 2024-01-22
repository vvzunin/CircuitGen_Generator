import { useField } from "formik";

const TextField = ({...props}) => {
  const [field, meta] = useField(props);

  const labelStyle = {
    width: props.labelWidth || '90px',
  };

  return (
    <label className={(meta.touched && meta.error) ? 'error' : ''}>
      {props.label}
      <input style={labelStyle} className={(meta.touched && meta.error) ? 'error' : ''} id={props.name} {...field} {...props} />
    </label>
  );
}

export default TextField;