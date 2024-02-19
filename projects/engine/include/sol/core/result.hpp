#ifndef _SOL_RESULT_HPP__
#define _SOL_RESULT_HPP__

#include <utility>

namespace sol::core
{
	template<typename SuccessType, typename ErrorType>
	class Result
	{
      public:
        static Result from_success(SuccessType s);
        static Result from_error(ErrorType e);

		[[nodiscard]] bool has_value() const noexcept;

		[[nodiscard]] SuccessType value() const noexcept;
        [[nodiscard]] ErrorType error() const noexcept;

	  private:
        bool _hasValue = false;
        bool _hasError = false;

		SuccessType _value;
        ErrorType _error;
	};

	template<typename SuccessType, typename ErrorType>
	Result<SuccessType, ErrorType> Result<SuccessType, ErrorType>::from_success(SuccessType s)
	{
        Result<SuccessType, ErrorType> res;
        res._value = std::move(s);
        res._hasValue = true;

		return res;
	}

	template <typename SuccessType, typename ErrorType>
	Result<SuccessType, ErrorType> Result<SuccessType, ErrorType>::from_error(ErrorType e)
	{
        Result<SuccessType, ErrorType> res;
        res._error = std::move(e);
        res._hasError = true;

		return res;
	}

	template <typename SuccessType, typename ErrorType>
    bool Result<SuccessType, ErrorType>::has_value() const noexcept
    {
        return _hasValue;
    }

    template <typename SuccessType, typename ErrorType>
    SuccessType Result<SuccessType, ErrorType>::value() const noexcept
    {
        return _value;
    }

    template <typename SuccessType, typename ErrorType>
    ErrorType Result<SuccessType, ErrorType>::error() const noexcept
    {
        return _error;
    }
}

#endif //_SOL_RESULT_HPP__